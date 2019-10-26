type denomType = {
  denom: string,
  nameList: list(string),
  count: int,
};

let denoms = [
  "a Very Low",
  "b Low Scores",
  "c Mid - Low",
  "d Mid - High",
  "e High",
  "f Very High"
];


let demonStringToInt = (demom) =>
  switch(demom) {
  |"a Very Low" => 1
  | "b Low Scores" => 2
  | "c Mid - Low" => 3
  | "d Mid - High" => 4
  | "e High" => 5
  | _ => 6
  };


let denominations = (score, mean, stdDevaition) =>
  switch (score) {
  | score when score < mean -. stdDevaition -. stdDevaition => "a Very Low"
  | score when score < mean -. stdDevaition => "b Low Scores"
  | score when score < mean => "c Mid - Low"
  | score when score < mean +. stdDevaition => "d Mid - High"
  | score when score < mean +. stdDevaition +. stdDevaition => "e High"
  | _ => "f Very High"
  };

let sum = (sample: list(float)): float =>
  Belt.List.reduce(sample, 0.0, (memo, value) => memo +. value);
let getMean = (sample: list(float)): float =>
  sum(sample) /. (sample |> Belt.List.length |> float_of_int);
/* 
let getSampleMean = (sample: list(float)): float =>
  sum(sample) /. (sample |> Belt.List.length |> float_of_int); */

let getStdDeviation = (sample: list(float)) => {
  let mean = getMean(sample);
  Belt.List.length(sample) == 1 || Belt.List.length(sample) == 0 ?
    0.0 :
    sample
    |> Belt.List.map(_, value => (value -. mean) *. (value -. mean))
    |> sum
    |> (
      summedValue =>
        sqrt(
          summedValue
          /. (sample |> Belt.List.length |> (n => n - 1 |> float_of_int)),
        )
    );
};

let transpose = (sample: list(list(float))) => {
  let first = Belt.List.head(sample);
  switch(first){
  | None => []
  | Some(first) =>
      first
      |> Belt.List.mapWithIndex(_, (idx, _) =>
          sample
          |> Belt.List.map(_, (innerList) => Belt.List.get(innerList, idx))
          |> Utils_List.removeOptionsFromList)
  }
}

let kr20 = (sample: list(list(float))): float => {
  let k =
    sample
    |> Belt.List.head
    |> Belt.Option.getWithDefault(_, [])
    |> Belt.List.length
    |> float_of_int;

  let sampleSums = Belt.List.map(sample, sum);

  let std = getStdDeviation(sampleSums);

  let variance = std *. std;

  let transposeSample = transpose(sample);

  let facilitySum =
    transposeSample
    |> Belt.List.map(_, (transposeRow) => {
      let facility = getMean(transposeRow);
      let inverseFacility = 1. -. facility;
      facility *. inverseFacility
    })
    |> sum;

  (k /. (k -. 1.)) *.(1. -. (facilitySum /. (variance *. variance)));
};

let phi = (sample: list(list(float))): float => {
  let n = Belt.List.length(sample) |> float_of_int;

  let k =
    sample
    |> Belt.List.head
    |> Belt.Option.getWithDefault(_, [])
    |> Belt.List.length
    |> float_of_int;

  let kr20 = kr20(sample);

  let sampleSums = Belt.List.map(sample, sum);

  let propSums = sampleSums |> Belt.List.map(_, sum => sum /. k)

  let propMean = propSums |> getMean;

  let propStd = propSums |> getStdDeviation;

  let propVariance = propStd *. propStd;

  let numerator = ((n *. propVariance) /. (n -. 1.)) *. kr20;

  let denomPart = ((propMean *. (1. -. propMean)) -. propStd) /. (k -. 1.);

  (numerator /. (numerator +. denomPart));
}

let getMax = (sample: list(float)) : option(float) => {
  sample
  |> Belt.List.toArray
  |> Belt.SortArray.stableSortBy(_, (a, b) => a > b ? -1 : 1)
  |> Belt.List.fromArray
  |> Belt.List.head
};

let getMin = (sample: list(float)) : option(float) => {
  sample
  |> Belt.List.toArray
  |> Belt.SortArray.stableSortBy(_, (a, b) => b > a ? -1 : 1)
  |> Belt.List.fromArray
  |> Belt.List.head
};

let getMedian = (sample: list(float)) : option(float) => {
  let numberElements = Belt.List.length(sample);

  let isEven = (numberElements mod 2) == 0;

  switch(isEven){
  | true => {
      let firstMiddleNumberIdx = (numberElements / 2) - 1;
      let sndMiddleNumberIdx = (numberElements / 2);

      let firstMiddleNum = Belt.List.get(sample, firstMiddleNumberIdx);
      let sndMiddleNumber = Belt.List.get(sample, sndMiddleNumberIdx);

      switch(firstMiddleNum, sndMiddleNumber){
      | (Some(first), Some(snd)) => Some((first +. snd) /. 2.)
      | _ => None
      }
    }
  | false => {
      let middleNumberIdx = (numberElements / 2);

      let middleNumber = Belt.List.get(sample, middleNumberIdx);

      switch(middleNumber){
      | (Some(middle)) => Some(middle)
      | _ => None
      }
    }
  }
};

let createScoreDenomHistogram =
    (
      studentScoreList: list((string, float)),
      (mean: float, stdDevaition: float),
    )
    : list(denomType) =>
  studentScoreList
  |> Belt.List.sort(_, ((_, scoreA), (_, scoreB)) =>
       scoreA -. scoreB < 0.0 ? 1 : (-1)
     )
  |> Belt.List.reduce(
       _,
       [],
       (memo, (name, studentScore)) => {
         let denominationStr =
           denominations(studentScore, mean, stdDevaition);
         memo
         |> Belt.List.getBy(_, ((denom, _, _)) => denom == denominationStr)
         |> (
           maybeScoreTuple =>
             switch (maybeScoreTuple) {
             | None => [(denominationStr, [name], 1), ...memo]
             | Some(_) =>
               Belt.List.map(memo, ((denom, nameList, count)) =>
                 denom == denominationStr ?
                   (denom, [name, ...nameList], count + 1) :
                   (denom, nameList, count)
               )
             }
         );
       },
     )
  |> Belt.List.map(_, ((denom, nameList, count)) =>
       {denom, nameList, count}
     );

let calculateZScore =
    (
      studentScoreList: list((string, float)),
      (mean: float, stdDevaition: float),
    )
    : list((string, float)) =>
  Belt.List.map(studentScoreList, ((name, score)) =>
    (name, stdDevaition != 0.0 ? (score -. mean) /. stdDevaition : 0.0)
  );