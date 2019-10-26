let getValueDoAction = (runOnVal, event) =>
  event
  |> ReactEventRe.Form.target
  |> ReactDOMRe.domElementToObj
  |> (domObj => domObj##value |> runOnVal)
  |> ignore;

let combineStyles = (outsideStyleMaybe, textAreaStyle) =>
  switch (outsideStyleMaybe) {
  | None => textAreaStyle
  | Some(style) => ReactDOMRe.Style.combine(textAreaStyle, style)
  };