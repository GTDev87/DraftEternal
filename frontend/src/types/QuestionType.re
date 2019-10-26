type t = [
  | `MULTIPLE_CHOICE
  | `LONG_ANSWER
  | `TRUE_FALSE
  | `FILL_IN_THE_BLANK
];

let all = () => [
  `MULTIPLE_CHOICE,
  `LONG_ANSWER,
  `TRUE_FALSE,
  `FILL_IN_THE_BLANK
];

let questionTypeToString = (questionType: t): string =>
  switch (questionType) {
  | `MULTIPLE_CHOICE => "Multiple Choice"
  | `LONG_ANSWER => "Long Response"
  | `TRUE_FALSE => "True False"
  | `FILL_IN_THE_BLANK => "Fill In The Blank"
  };