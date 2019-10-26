type t = string;

[@bs.module] external generateUUID: unit => t = "uuid/v4";
[@bs.module] external generateUUIDV5: (t, t) => t = "uuid/v5";

let globalV4 = generateUUID();

type randGenerator;
[@bs.module] external create: t => randGenerator = "random-seed";
[@bs.send] external getString: (randGenerator, int) => string = "string";
let random: randGenerator = create(globalV4);

let geneateGlobalRandomString = () => getString(random, 32);

let globalRandomString = geneateGlobalRandomString();

/* (random, seed) */

/* module type V5Type = {
     let generateRandom: unit => string;
     let namespace: string;
   }; */

module type UUIDSeedType = {let namespace: string;};

module V5Random = (UUIDSeed: UUIDSeedType) => {
  let namespace = UUIDSeed.namespace;

  let generateSeqUUID = () => generateUUIDV5(globalRandomString, namespace);
};