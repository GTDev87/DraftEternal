let removeOptionsFromList = (list : list(option('a))) : list('a) =>
  Belt.List.reduce(list, [], (memo, ele) =>
    switch(ele){
    | None => memo
    | Some(value) => memo @ [value]
    }
  );

let joinStringList = (listString : list(string), glue : string) : string =>
  Belt.List.reduce(listString, "", (memo, ele) => (memo ++ ((memo == "") ? ele : glue ++ ele)));

let updateIfDifferent = (list, newItem) =>
  list
  |> Belt.List.getBy(_, (item) => item == newItem)
  |> (maybeItem) =>
       switch(maybeItem) {
       | None => list @ [newItem]
       | Some(_) => list
       }
;