type t = [
  | `PUBLIC
  | `PRIVATE
  | `UNLISTED
];

let all = () => [
  `PUBLIC,
  `PRIVATE,
  `UNLISTED,
];

let toString = (t: t): string =>
  switch (t) {
  | `PUBLIC => "Public"
  | `PRIVATE => "Private"
  | `UNLISTED => "Unlisted"
  };