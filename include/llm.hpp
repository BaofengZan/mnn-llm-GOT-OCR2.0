//
//  llm.hpp
//
//  Created by MNN on 2023/08/25.
//  ZhaodeWang
//

#ifndef LLM_hpp
#define LLM_hpp

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <functional>
#include <unordered_map>

#include <MNN/AutoTime.hpp>
#include <MNN/expr/Expr.hpp>
#include <MNN/expr/Module.hpp>
#include <MNN/expr/MathOp.hpp>
#include <MNN/expr/NeuralNetWorkOp.hpp>
#include "tokenizer.hpp"
#include "json.hpp"

using namespace MNN;
using namespace Express;
using json = nlohmann::json;
class Tokenizer;
class Pipeline;

// Llm start
// llm stream buffer with callback
class LlmStreamBuffer : public std::streambuf {
public:
    using CallBack = std::function<void(const char* str, size_t len)>;;
    LlmStreamBuffer(CallBack callback) : callback_(callback) {}

protected:
    virtual std::streamsize xsputn(const char* s, std::streamsize n) override {
        if (callback_) {
            callback_(s, n);
        }
        return n;
    }

private:
    CallBack callback_ = nullptr;
};

enum PROMPT_TYPE {
    SYSTEM = 0,
    ATTACHMENT = 1,
    USER = 2,
    ASSISTANT = 3,
    OTHER = 4
};

struct Prompt {
    PROMPT_TYPE type;
    std::string str;
    std::vector<int> tokens;
};

class LlmConfig {
public:
    LlmConfig() {}
    LlmConfig(const std::string& path) {
        std::ifstream config_file(path);
        if (config_file.is_open()) {
            config_ = json::parse(config_file);
        } else {
            std::cerr << "Unable to open config file: " << path << std::endl;
        }
        // get config base dir
        size_t pos = path.find_last_of("/\\");
        if (pos == std::string::npos) {
            base_dir_ = "./";
        } else {
            base_dir_ = path.substr(0, pos + 1);
        }
    }

    std::string model_type() const {
        return config_.value("model_type", "unknow");
    }

    std::string llm_model() const {
        return base_dir_ + config_.value("llm_model", "llm.mnn");
    }

    std::string llm_weight() const {
        return base_dir_ + config_.value("llm_weight", "llm.mnn.weight");
    }

    std::string block_model(int index) const {
        return base_dir_ + config_.value("block_model", "block_") + std::to_string(index) + ".mnn";
    }

    std::string lm_model() const {
        return base_dir_ + config_.value("lm_model", "lm.mnn");
    }

    std::string embedding_model() const {
        return base_dir_ + config_.value("embedding_model", "embedding.mnn");
    }

    std::string embedding_file() const {
        return base_dir_ + config_.value("embedding_file", "embeddings_bf16.bin");
    }

    std::string tokenizer_file() const {
        return base_dir_ + config_.value("tokenizer_file", "tokenizer.txt");
    }

    bool is_single() const {
        return config_.value("is_single", true);
    }

    int max_new_tokens() const {
        return config_.value("max_new_tokens", 512);
    }

    int hidden_size() const {
        return config_.value("hidden_size", 4096);
    }

    int layer_nums() const {
        return config_.value("layer_nums", 32);
    }

    std::vector<int> key_value_shape() const {
        return config_.value("key_value_shape", std::vector<int>{});
    }

    std::string attention_mask() const {
        return config_.value("attention_mask", "int");
    }

    std::string prompt_template() const {
        return config_.value("prompt_template", "");
    }

    std::string backend_type() const {
        return config_.value("backend_type", "cpu");
    }

    int thread_num() const {
        return config_.value("thread_num", 4);
    }

    std::string precision() const {
        return config_.value("precision", "low");
    }

    std::string memory() const {
        return config_.value("memory", "low");
    }
private:
    std::string base_dir_;
    json config_;
};

class Llm {
public:
    Llm(std::shared_ptr<LlmConfig> config) : config_(config) {}
    virtual ~Llm() {
        modules_.clear();
        visual_module_.reset();
        runtime_manager_.reset();
    }
    static Llm* createLLM(const std::string& config_path);
    void load();
    void chat();
    VARP forward(const std::vector<int>& input_ids);
    int sample(VARP logits, const std::vector<int>& pre_ids);
    std::string apply_chat_template(const std::string& input_str) const;
    std::string response(const std::string& input_str, std::ostream* os = &std::cout, const char* end_with = nullptr);
    void generate_init();
    std::string generate(const std::vector<int>& input_ids, std::ostream* os, const char* end_with);
    std::vector<int> generate(const std::vector<int>& input_ids, int max_new_tokens = -1);
    void print_speed();
    friend class Pipeline;
public:
    // TODO
    std::string model_name_ = "";
    bool is_single_ = true;
    bool is_disk_embedding_ = true;
    bool is_visual_ = false;
    int layer_nums_ = 0;
    int hidden_size_ = 4096;
    // config
    int max_new_tokens_ = 1024;
    int backend_type_ = 0;
    // forward info
    int prompt_len_ = 0;
    int gen_seq_len_ = 0;
    int all_seq_len_ = 0;
    // time
    int64_t prefill_us_ = 0;
    int64_t decode_us_ = 0;
    std::shared_ptr<LlmConfig> config_;
    std::unique_ptr<Tokenizer> tokenizer_;
protected:
    VARP embedding(const std::vector<int>& input_ids);
    VARP txt_embedding(const std::vector<int>& input_ids);
    std::string decode(int id);
protected:
    std::vector<int> key_value_shape_ = {};
    VARP inputs_embeds_, attention_mask_, position_ids_;
    std::shared_ptr<Module> visual_module_;
    std::shared_ptr<Executor::RuntimeManager> runtime_manager_;
    std::vector<std::shared_ptr<Module>> modules_;
    std::vector<VARP> past_key_values_;
private:
    virtual VARP visual_embedding(const std::vector<int>& input_ids) { return nullptr; }
    virtual VARP gen_attention_mask(int seq_len);
    virtual VARP gen_position_ids(int seq_len);
    virtual bool is_stop(int token_id);
};

#if 0
// some llm models
class Chatglm_6b : public Llm {
public:
    Chatglm_6b() {
        model_name_ = "Chatglm_6b";
        layer_nums_ = 28;
        key_value_shape_ = {2, 0, 1, 32, 128};
    }
private:
    virtual VARP gen_attention_mask(int seq_len) override;
    virtual VARP gen_position_ids(int seq_len) override;
    virtual bool is_stop(int token_id) override;
    int context_len_ = 0;
};
/*
class Phi_2 : public Chatglm2_6b {
public:
    Phi_2() {
        model_name_ = "Phi_2";
        layer_nums_ = 32;
        key_value_shape_ = {1, 0, 2, 32, 80};
        hidden_size_ = 2560;
        tokenizer_.reset(new Tiktoken);
    }
private:
    virtual std::vector<int> tokenizer(const std::string& query) override;
    virtual bool is_stop(int token_id) override;
};
*/

class Qwen_vl : public Llm {
public:
    Qwen_vl() {
        model_name_ = "Qwen_vl";
        is_visual_ = true;
        layer_nums_ = 32;
        key_value_shape_ = {2, 1, 0, 32, 128};
        hidden_size_ = 4096;
        tokenizer_.reset(new Tiktoken);
    }
private:
    const int img_size_ = 448;
    const int imgpad_len_ = 256;
    const int img_start_ = 151857;
    const int img_end_ = 151858;
    const int img_pad_ = 151859;
private:
    std::vector<int> url_encode(const std::string& url);
    virtual VARP visual_embedding(const std::vector<int>& input_ids) override;
    virtual VARP gen_attention_mask(int seq_len) override;
};

class Llama2_7b : public Llm {
public:
    Llama2_7b() {
        model_name_ = "Llama2_7b";
        layer_nums_ = 32;
        key_value_shape_ = {2, 1, 32, 0, 128};
    }
private:
    virtual VARP gen_attention_mask(int seq_len) override;
    virtual VARP gen_position_ids(int seq_len) override;
    virtual bool is_stop(int token_id) override;
};

class Yi_6b : public Llama2_7b {
public:
    Yi_6b() {
        model_name_ = "Yi_6b";
        key_value_shape_ = {2, 1, 4, 0, 128};
    }
private:
    virtual bool is_stop(int token_id) override;
};
#endif
// Llm end

// Embedding start
class Embedding {
public:
    Embedding() {
        // default tokenier is Bert
        tokenizer_.reset(new BertTokenizer);
    }
    virtual ~Embedding() {
        module_.reset();
        runtime_manager_.reset();
    }
    static Embedding* createEmbedding(const std::string& path, std::string model_type = "auto");
    static float dist(VARP var0, VARP var1);
    void load(const std::string& model_dir);
    VARP embedding(const std::string& txt);
    void print_speed();
    int dim() { return hidden_size_; }
public:
    // time
    int64_t embedding_us_ = 0;
    int prompt_len_ = 0;
protected:
    // model configs
    int layer_nums_ = 0;
    int hidden_size_ = 1024;
    std::string model_name_ = "";
    // tokenizer
    std::unique_ptr<Tokenizer> tokenizer_;
private:
    virtual std::vector<int> tokenizer(const std::string& query) = 0;
    virtual VARP gen_attention_mask(int seq_len) = 0;
    virtual VARP gen_position_ids(int seq_len) = 0;
private:
    // MNN Modules
    std::shared_ptr<Executor::RuntimeManager> runtime_manager_;
    std::shared_ptr<Module> module_;
    // model dir
    std::string model_dir_;
};

// some embedding models
class Bge : public Embedding {
public:
    Bge() {
        model_name_ = "Bge";
        layer_nums_ = 24;
        hidden_size_ = 1024;
    }
private:
    virtual std::vector<int> tokenizer(const std::string& query) override;
    virtual VARP gen_attention_mask(int seq_len) override;
    virtual VARP gen_position_ids(int seq_len) override;
};

// Embedding end

// TextVectorStore strat
class TextVectorStore {
public:
    TextVectorStore() : embedding_(nullptr) {}
    TextVectorStore(std::shared_ptr<Embedding> embedding) : embedding_(embedding) {}
    ~TextVectorStore() {}
    static TextVectorStore* load(const std::string& path, const std::string& embedding_path = "");
    void set_embedding(std::shared_ptr<Embedding> embedding) {
        embedding_ = embedding;
    }
    void save(const std::string& path);
    void add_text(const std::string& text);
    void add_texts(const std::vector<std::string>& texts);
    std::vector<std::string> search_similar_texts(const std::string& txt, int topk = 1);
    void bench();
protected:
    inline VARP text2vector(const std::string& text);
// private:
public:
    std::shared_ptr<Embedding> embedding_;
    VARP vectors_;
    std::vector<std::string> texts_;
    int dim_ = 1024;
};
// TextVectorStore end

// Document start
class Document {
public:
    enum DOCTYPE {
        AUTO = 0,
        TXT  = 1,
        MD   = 2,
        HTML = 3,
        PDF  = 4
    };
    Document(const std::string& path, DOCTYPE type = AUTO) : path_(path), type_(type) {}
    ~Document() = default;
    std::vector<std::string> split(int chunk_size = -1);
private:
    DOCTYPE type_;
    std::string path_;
    std::vector<std::string> load_txt();
    std::vector<std::string> load_pdf();
};
// Document end

// MemoryBase start
class MemoryBase {
public:
    MemoryBase() {}
    virtual ~MemoryBase() {}
    void set_embedding(std::shared_ptr<Embedding> embedding) {
        store_->set_embedding(embedding);
    }
    virtual std::vector<std::string> search(const std::string& query, int topk);
    virtual void save(const std::string& path) = 0;
    virtual void build_vectors() = 0;
protected:
    void load_store(const std::string& path);
    void save_store(const std::string& path);
public:
    std::shared_ptr<TextVectorStore> store_;
};

class ChatMemory : public MemoryBase {
public:
    ChatMemory() {}
    ~ChatMemory() override {}
    static ChatMemory* load(const std::string& path);
    void save(const std::string& path) override;
    void build_vectors() override;
    std::string get_latest(std::string key);
    void add(const std::vector<Prompt>& prompts);
    void summarize(std::shared_ptr<Llm> llm);
private:
    json memory_;
};

class Knowledge : public MemoryBase {
public:
    Knowledge() {}
    ~Knowledge() override {}
    static Knowledge* load(const std::string& path);
    void save(const std::string& path) override;
    void build_vectors() override;
private:
    std::unique_ptr<Document> document_;
};
// MemoryBase end

// Pipeline start
class Pipeline {
public:
    Pipeline() {}
    ~Pipeline() {}
    static Pipeline* load(const std::string& path);
    void invoke(const std::string& str);
private:
    bool need_memory(const std::string& str);
    bool need_knowledge(const std::string& str);
    std::string build_prompt(const std::string& str);
    std::unique_ptr<Llm> llm_;
    std::shared_ptr<Embedding> embedding_;
    std::unique_ptr<Knowledge> knowledge_;
    std::unique_ptr<ChatMemory> memory_;
    std::string system_, user_, assistant_;
    std::vector<Prompt> prompts_;
    json config_;
};
// Pipeline end

#endif // LLM_hpp
