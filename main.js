const fs = require("fs");

const factory = require("./file_block.js");

const BLOCK_SIZE = 2097152;

let wasmFns = null;
const getWasmFns = async () => {
  if (!wasmFns) {
    wasmFns = await factory();
  }

  return wasmFns;
};

const transformASMFileResult = (parts) => {
  const array = [];
  for (let i = 0; i < parts.size(); i++) {
    const part = parts.get(i);
    const obj = {
      partNum: part.part_num,
      endOffset: part.end_offset,
      cumulateSha1: part.cumulate_sha1,
    };
    array.push(obj);
  }
  return array;
};

const generateFileBlockDigest = async (file) => {
  if (typeof file === "string") {
    file = fs.readFileSync(file);
  }

  const wasmFns = await getWasmFns();

  const fileParts = transformASMFileResult(
    wasmFns.generateFileBlockDigest(file).parts
  );

  const fileSize = file.length;
  const blockSha = [];
  const blockBase64 = [];

  fileParts.forEach((part) => {
    blockSha.push(part.cumulateSha1);
    blockBase64.push(
      file.slice(part.endOffset - BLOCK_SIZE, part.endOffset).toString("base64")
    );
  });

  return {
    fileSize,
    blockSha,
    blockBase64,
  };
};

exports.generateFileBlockDigest = generateFileBlockDigest;
