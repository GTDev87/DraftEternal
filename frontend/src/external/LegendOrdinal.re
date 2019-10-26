[@bs.module "@vx/legend"]
external comp : ReasonReact.reactClass = "LegendOrdinal";

type datumType('a) = {
  .
  "datum": 'a
};

let make = (
  ~direction : string,
  ~scale : ('a) => 'b,
  ~shape : string,
  ~fill : (datumType('a)) => 'b,
  ~labelFormat : ('a) => string,
  ~domain=?,
  children
) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "direction": direction,
      "scale": scale,
      "shape":shape,
      "domain": Js.Nullable.fromOption(domain),
      "fill": fill,
      "labelFormat": labelFormat,
    },
    children
  );
