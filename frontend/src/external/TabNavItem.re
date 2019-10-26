[@bs.module "reactstrap"]
external tab : ReasonReact.reactClass = "NavItem";

let make = (~className=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=tab,
    ~props={
      "className":
        "NavItem " ++
          (
            className
            |> Belt.Option.getWithDefault(_, "")
          ),
    },
    children
  );
