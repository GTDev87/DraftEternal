let timeCheck = (prevTime, label) => {
  let time = Js.Date.now();
  Js.log("diff " ++ label);
  Js.log(time -. prevTime);
  time
};

let combineStyles = (outsideStyleMaybe, textAreaStyle) =>
  switch (outsideStyleMaybe) {
  | None => textAreaStyle
  | Some(style) => ReactDOMRe.Style.combine(textAreaStyle, style)
  };