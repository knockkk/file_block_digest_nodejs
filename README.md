# 企业微信微盘文件分块上传 Node.js 版本

企业微信上传大文件要求开发者在本地对大文件进行分块以及计算分块的`累积sha值`，如下图所示。官方只提供了 C++版本的[Demo](https://github.com/wecomopen/file_block_digest)。在 Node.js 中，如果使用内置的`sha1`（`crypto.createHash('sha1')`）算法，计算结果会与官方 C++ Demo 的计算结果存在差异，导致上传报错。

此版本使用[Emscripten](https://emscripten.org/index.html)将官方 C++ Demo 编译为了 wasm 代码，并可在 Node.js 中正常运行，得到正确的 sha 值。

![img](https://raw.githubusercontent.com/knockkk/file_block_digest_nodejs/main/example/upload.png)

# 如何使用

只需将`index.js`、`file_block.js` 与`file_block.wasm` 三个文件拷贝到个人项目中即可。使用方式参考`example/test.js`：

```js
const { resolve } = require("path");

const { generateFileBlockDigest } = require("..");

const run = async () => {
  // 调用 generateFileBlockDigest 函数，参数为文件buffer值或文件路径
  const fileBlockDigest = await generateFileBlockDigest(
    resolve(__dirname, "./sha_calc_demo.txt")
  );

  console.log(fileBlockDigest);
};

run();
```

运行`node example/test.js`，打印结果如下：

```json
{
  "fileSize": 5999998,
  "blockSha": [
    "5186fee37e9f7e77a1f6bea8d4e32638d5186d44",
    "cf540965f3190bc0c6367147ab0ac64dc9eff6a0",
    "bda1e884e1cb23a5cbdea73d2e00e23baa72d2f5"
  ],
  "blockBase64": ["MTIzNDU2Nzg5MA0KMTIz...", "...", "..."]
}
```

# 如何编译

1. 本地安装`emcc`命令
2. `cd cpp & bash build.sh`
