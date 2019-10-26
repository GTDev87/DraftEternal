
let baseHeaderStyles =
  ReactDOMRe.Style.make(
    ~padding=".3em 0",
    ~marginBottom="1em",
    ~width="100%",
    ~borderBottom="solid 1px gray",
    (),
  );

let headerStyle = style =>
  switch (style) {
  | Some(style) => ReactDOMRe.Style.combine(baseHeaderStyles, style)
  | None => baseHeaderStyles
  };

[@react.component]
let make = (~style=?, ~children) => {
  <div style=headerStyle(style)>
    {children}
  </div>
};