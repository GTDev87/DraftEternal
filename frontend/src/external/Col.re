[@bs.module "reactstrap"]
external col : ReasonReact.reactClass = "Col";

let make = (~style=?, ~xs=?, ~md=?, ~orderMd=?, ~orderXs=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=col,
    ~props={
      "style": Js.Nullable.fromOption(style),
      "xs":
        xs
        |> Belt.Option.mapWithDefault(_, None, (xs) => Some({
          "size": xs,
          "order": Belt.Option.getWithDefault(orderXs, 1)
        }))
        |> Js.Nullable.fromOption,
      "md":
        md
        |> Belt.Option.mapWithDefault(_, None, (md) => Some({
          "size": md,
          "order": Belt.Option.getWithDefault(orderMd, 1)
        }))
        |> Js.Nullable.fromOption,
    },
    children
  );