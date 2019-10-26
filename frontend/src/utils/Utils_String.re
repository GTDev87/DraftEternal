

let stringToDivHtml = string =>
  string
  |> Js_string.split("\n", _)
  |> Belt.List.fromArray
  |> Belt.List.reduce(
       _,
       [],
       (memo, splitString) => {
         let rand = Random.randomString();
         memo == [] ?
           memo @ [ReasonReact.string(splitString)] :
           memo @ [<br key=rand />] @ [ReasonReact.string(splitString)];
       },
     )
  |> Utils_ReasonReact.listToReactArray;

let toStringWithPercision = (number : float, digits : int) : string =>
  number |> Js.Float.toFixedWithPrecision(_, ~digits);

