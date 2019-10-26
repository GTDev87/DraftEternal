[@bs.module "react-sidenav"]
external comp : ReasonReact.reactClass = "Nav";

let make = (~id=?, ~tupleId=?, children) => {
  let finalId =
    switch(id, tupleId){
    | (_, Some((id1, id2))) => id1 ++ "@@@@" ++ id2
    | (Some(id), _) => id
    | _ => ""
    };
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "id": finalId,
    },
    children
  )
};