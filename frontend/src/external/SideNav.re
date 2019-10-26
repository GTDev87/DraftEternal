[@bs.module "react-sidenav"]
external comp : ReasonReact.reactClass = "default";

let make = (~highlightColor=?, ~highlightBgColor=?, ~defaultSelected=?, ~selected=?, ~tupleSelected=?, ~onItemSelection=?, ~tupleOnItemSelection=?, children) => {
  let finalOnItemSelection =
    switch(onItemSelection, tupleOnItemSelection){
    | (_, Some(tupleOnItemSelection)) =>
        Some(
          (idString) => {
            let splitList = (idString |> Js_string.split("@@@@", _) |> Belt.List.fromArray);
            let [a, b, ..._c] = splitList;
            tupleOnItemSelection(a,b);
          }
        )
    | (Some(onItemSelection), None) => Some(onItemSelection)
    | _ => None
    };

  let finalSelected =
    switch(selected, tupleSelected){
    | (_, Some((id1, id2))) => Some(id1 ++ "@@@@" ++ id2)
    | (Some(selected), _) => Some(selected)
    | _ => None
    };

  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "selected": Js.Nullable.fromOption(finalSelected),
      "onItemSelection": Js.Nullable.fromOption(finalOnItemSelection),
      "highlightColor": Js.Nullable.fromOption(highlightColor),
      "highlightBgColor": Js.Nullable.fromOption(highlightBgColor),
      "defaultSelected": Js.Nullable.fromOption(defaultSelected),
    },
    children
  );
};