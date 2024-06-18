![mnn-llm](resource/logo.png)

# mnn-llm
[![License](https://img.shields.io/github/license/wangzhaode/mnn-llm)](LICENSE.txt)
[![Download](https://img.shields.io/github/downloads/wangzhaode/mnn-llm/total)](https://github.com/wangzhaode/mnn-llm/releases)

[English](./README_en.md)

## 示例工程

- [cli](./demo/cli_demo.cpp): 使用命令行编译，android编译参考[android_build.sh](./script/android_build.sh)
- [web](./demo/web_demo.cpp): 使用命令行编译，运行时需要指定[web资源](./web)
- [android](./android/): 使用Android Studio打开编译；
- [ios](./ios/README.md): 使用Xcode打开编译；🚀🚀🚀**该示例代码100%由ChatGPT生成**🚀🚀🚀
- [python](./python/README.md): 对mnn-llm的python封装`mnnllm`；
- [other](./demo): 新增文本embedding，向量查询，文本解析，记忆库与知识库能力🔥；

## 模型导出与下载

llm模型导出`onnx`和`mnn`模型请使用[llm-export](https://github.com/wangzhaode/llm-export)

`modelscope`模型下载：

<details>
  <summary>qwen系列</summary>

- [modelscope-qwen-1.8b-chat]
- [modelscope-qwen-7b-chat]
- [modelscope-qwen-vl-chat]
- [modelscope-qwen1.5-0.5b-chat]
- [modelscope-qwen1.5-1.8b-chat]
- [modelscope-qwen1.5-4b-chat]
- [modelscope-qwen1.5-7b-chat]
- [modelscope-qwen2-0.5b-chat]
- [modelscope-qwen2-1.5b-chat]
- [modelscope-qwen2-7b-chat]

</details>

<details>
  <summary>glm系列</summary>

- [modelscope-chatglm-6b]
- [modelscope-chatglm2-6b]
- [modelscope-codegeex2-6b]
- [modelscope-chatglm3-6b]
- [modelscope-glm4-9b-chat]

</details>

<details>
  <summary>llama系列</summary>

- [modelscope-llama2-7b-chat]
- [modelscope-llama3-8b-instruct]
- [modelscope-baichuan2-7b-chat]
- [modelscope-internlm-chat-7b]
- [modelscope-yi-6b-chat]
- [modelscope-deepseek-7b-chat]
- [modelscope-tinyllama-1.1b-chat]

</details>

<details>
  <summary>其他</summary>

- [modelscope-phi-2]
- [modelscope-bge-large-zh]

</details>


[modelscope-qwen-1.8b-chat]: https://modelscope.cn/models/zhaode/Qwen-1_8B-Chat-MNN/files
[modelscope-qwen-7b-chat]: https://modelscope.cn/models/zhaode/Qwen-7B-Chat-MNN/files
[modelscope-qwen-vl-chat]: https://modelscope.cn/models/zhaode/Qwen-VL-Chat-MNN/files
[modelscope-qwen1.5-0.5b-chat]: https://modelscope.cn/models/zhaode/Qwen1.5-0.5B-Chat-MNN/files
[modelscope-qwen1.5-1.8b-chat]: https://modelscope.cn/models/zhaode/Qwen1.5-1.8B-Chat-MNN/files
[modelscope-qwen1.5-4b-chat]: https://modelscope.cn/models/zhaode/Qwen1.5-4B-Chat-MNN/files
[modelscope-qwen1.5-7b-chat]: https://modelscope.cn/models/zhaode/Qwen1.5-7B-Chat-MNN/files
[modelscope-qwen2-0.5b-chat]: https://modelscope.cn/models/zhaode/Qwen2-0.5B-Instruct-MNN/files
[modelscope-qwen2-1.5b-chat]: https://modelscope.cn/models/zhaode/Qwen2-1.5B-Instruct-MNN/files
[modelscope-qwen2-7b-chat]: https://modelscope.cn/models/zhaode/Qwen2-7B-Instruct-MNN/files

[modelscope-chatglm-6b]: https://modelscope.cn/models/zhaode/chatglm-6b-MNN/files
[modelscope-chatglm2-6b]: https://modelscope.cn/models/zhaode/chatglm2-6b-MNN/files
[modelscope-codegeex2-6b]: https://modelscope.cn/models/zhaode/codegeex2-6b-MNN/files
[modelscope-chatglm3-6b]: https://modelscope.cn/models/zhaode/chatglm3-6b-MNN/files
[modelscope-glm4-9b-chat]: https://modelscope.cn/models/zhaode/glm-4-9b-chat-MNN/files

[modelscope-llama2-7b-chat]: https://modelscope.cn/models/zhaode/Llama-2-7b-chat-MNN/files
[modelscope-llama3-8b-instruct]: https://modelscope.cn/models/zhaode/Llama-3-8B-Instruct-MNN/files
[modelscope-baichuan2-7b-chat]: https://modelscope.cn/models/zhaode/Baichuan2-7B-Chat-MNN/files
[modelscope-internlm-chat-7b]: https://modelscope.cn/models/zhaode/internlm-chat-7b-MNN/files
[modelscope-yi-6b-chat]: https://modelscope.cn/models/zhaode/Yi-6B-Chat-MNN/files
[modelscope-deepseek-7b-chat]: https://modelscope.cn/models/zhaode/deepseek-llm-7b-chat-MNN/files
[modelscope-tinyllama-1.1b-chat]: https://modelscope.cn/models/zhaode/TinyLlama-1.1B-Chat-MNN/files
[modelscope-phi-2]: https://modelscope.cn/models/zhaode/phi-2-MNN/files
[modelscope-bge-large-zh]: https://modelscope.cn/models/zhaode/bge-large-zh-MNN/files

## 构建

CI构建状态：

[![Build Status][pass-linux]][ci-linux]
[![Build Status][pass-macos]][ci-macos]
[![Build Status][pass-windows]][ci-windows]
[![Build Status][pass-android]][ci-android]
[![Build Status][pass-ios]][ci-ios]
[![Build Status][pass-python]][ci-python]

[pass-linux]: https://github.com/wangzhaode/mnn-llm/actions/workflows/linux.yml/badge.svg
[pass-macos]: https://github.com/wangzhaode/mnn-llm/actions/workflows/macos.yml/badge.svg
[pass-windows]: https://github.com/wangzhaode/mnn-llm/actions/workflows/windows.yml/badge.svg
[pass-android]: https://github.com/wangzhaode/mnn-llm/actions/workflows/android.yml/badge.svg
[pass-ios]: https://github.com/wangzhaode/mnn-llm/actions/workflows/ios.yml/badge.svg
[pass-python]: https://github.com/wangzhaode/mnn-llm/actions/workflows/python.yml/badge.svg
[ci-linux]: https://github.com/wangzhaode/mnn-llm/actions/workflows/linux.yml
[ci-macos]: https://github.com/wangzhaode/mnn-llm/actions/workflows/macos.yml
[ci-windows]: https://github.com/wangzhaode/mnn-llm/actions/workflows/windows.yml
[ci-android]: https://github.com/wangzhaode/mnn-llm/actions/workflows/android.yml
[ci-ios]: https://github.com/wangzhaode/mnn-llm/actions/workflows/ios.yml
[ci-python]: https://github.com/wangzhaode/mnn-llm/actions/workflows/python.yml

### 本地编译
```
# linux
./script/build.sh

# macos
./script/build.sh

# windows msvc
./script/build.ps1

# python wheel
./script/py_build.sh

# android
./script/android_build.sh

# android apk
script/android_app_build.sh
```

一些编译宏：
- `BUILD_FOR_ANDROID`: 编译到Android设备；
- `USING_VISUAL_MODEL`: 支持多模态能力的模型，需要依赖`libMNNOpenCV`；
- `DUMP_PROFILE_INFO`: 每次对话后dump出性能数据到命令行中；

默认使用`CPU`后端且不实用多模态能力，如果使用其他后端或能力，可以在编译MNN的脚本中添加`MNN`编译宏
- cuda: `-DMNN_CUDA=ON`
- opencl: `-DMNN_OPENCL=ON`
- opencv: `-DMNN_BUILD_OPENCV=ON -DMNN_IMGCODECS=ON`

### 4. 执行

```bash
# linux/macos
./cli_demo ./Qwen2-1.5B-Instruct-MNN/config.json # cli demo
./web_demo ./Qwen2-1.5B-Instruct-MNN/config.json ../web # web ui demo

# windows
.\Debug\cli_demo.exe ./Qwen2-1.5B-Instruct-MNN/config.json
.\Debug\web_demo.exe ./Qwen2-1.5B-Instruct-MNN/config.json ../web

# android
adb push libs/*.so build/libllm.so build/cli_demo /data/local/tmp
adb push model_dir /data/local/tmp
adb shell "cd /data/local/tmp && export LD_LIBRARY_PATH=. && ./cli_demo ./Qwen2-1.5B-Instruct-MNN/config.json"
```


## Reference
<details>
  <summary>reference</summary>

- [chatglm-6b](https://modelscope.cn/models/ZhipuAI/chatglm-6b/summary)
- [chatglm2-6b](https://modelscope.cn/models/ZhipuAI/chatglm2-6b/summary)
- [chatglm3-6b](https://modelscope.cn/models/ZhipuAI/chatglm3-6b/summary)
- [codegeex2-6b](https://modelscope.cn/models/ZhipuAI/codegeex2-6b/summary)
- [Baichuan2-7B-Chat](https://modelscope.cn/models/baichuan-inc/baichuan-7B/summary)
- [Qwen-7B-Chat](https://modelscope.cn/models/qwen/Qwen-7B-Chat/summary)
- [Qwen-VL-Chat](https://modelscope.cn/models/qwen/Qwen-VL-Chat/summary)
- [Qwen-1.8B-Chat](https://modelscope.cn/models/qwen/Qwen-1_8B-Chat/summary)
- [Llama-2-7b-chat-ms](https://modelscope.cn/models/modelscope/Llama-2-7b-chat-ms/summary)
- [internlm-chat-7b](https://modelscope.cn/models/Shanghai_AI_Laboratory/internlm-chat-7b/summary)
- [phi-2](https://modelscope.cn/models/AI-ModelScope/phi-2/summary)
- [bge-large-zh](https://modelscope.cn/models/AI-ModelScope/bge-large-zh/summary)
- [TinyLlama-1.1B-Chat-v0.6](https://huggingface.co/TinyLlama/TinyLlama-1.1B-Chat-v0.6)
- [Yi-6B-Chat](https://modelscope.cn/models/01ai/Yi-6B-Chat/summary)
- [Qwen1.5-0.5B-Chat](https://modelscope.cn/models/qwen/Qwen1.5-0.5B-Chat/summary)
- [Qwen1.5-1.8B-Chat](https://modelscope.cn/models/qwen/Qwen1.5-1.8B-Chat/summary)
- [Qwen1.5-4B-Chat](https://modelscope.cn/models/qwen/Qwen1.5-4B-Chat/summary)
- [Qwen1.5-7B-Chat](https://modelscope.cn/models/qwen/Qwen1.5-7B-Chat/summary)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [chatgpt-web](https://github.com/xqdoo00o/chatgpt-web)
- [ChatViewDemo](https://github.com/BrettFX/ChatViewDemo)
- [nlohmann/json](https://github.com/nlohmann/json)

</details>