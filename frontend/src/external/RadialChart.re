[@bs.module "@data-ui/radial-chart"]
external comp : ReasonReact.reactClass = "RadialChart";

type margin = {
  .
  "top": int,
  "bottom": int,
  "left": int,
  "right": int
};

type pieData('a) = {
  .
  "datum": 'a,
  "fraction": float
};

let make = (
  ~ariaLabel : string,
  ~margin : margin,
  ~width : float,
  ~height : float,
  ~renderTooltip : (pieData('a)) => ReasonReact.reactElement,
  children
) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=comp,
    ~props={
      "ariaLabel": ariaLabel,
      "margin": margin,
      "width": width,
      "height": height,
      "renderTooltip": renderTooltip,
    },
    children
  );
