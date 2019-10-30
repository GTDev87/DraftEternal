type t = [
  | `FIRE
  | `JUSTICE
  | `PRIMAL
  | `SHADOW
  | `TIME
];

let all = () => [
  `FIRE,
  `JUSTICE,
  `PRIMAL,
  `SHADOW,
  `TIME,
];

let questionTypeToString = (t: t): string =>
  switch (t) {
  | `FIRE => "Fire"
  | `JUSTICE => "Justice"
  | `PRIMAL => "Primal"
  | `SHADOW => "Shadow"
  | `TIME => "Time"
  };