type t =
  | Overview
  | Score
  | Objective
  | Question
;

let all = [Overview, Score, Objective, Question];

let resultTypeTabToString = (resultTypeTab) =>
  switch(resultTypeTab){
  | Overview => "Overview"
  | Score => "Score"
  | Objective => "Objective"
  | Question => "Question"
  };
