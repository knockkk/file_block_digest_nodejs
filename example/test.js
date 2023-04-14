const { resolve } = require("path");

const { generateFileBlockDigest } = require("..");

const run = async () => {
  const fileBlockDigest = await generateFileBlockDigest(
    resolve(__dirname, "./sha_calc_demo.txt")
  );

  console.log(fileBlockDigest);
};

run();
