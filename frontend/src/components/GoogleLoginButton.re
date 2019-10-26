
let buttonStyle = ReactDOMRe.Style.make(~width="100%", ());

let aStyle = style =>
  Utils.Dom.combineStyles(
    style,
    ReactDOMRe.Style.make(
      ~width="100%",
      ~backgroundColor="red",
      ~display="flex",
      ~justifyContent="center",
      ~color="white",
      ~padding="1em 0",
      (),
    ),
  );

  [@react.component]
let make = (~style=?) => {
  <a
    style={aStyle(style)}
    href={Config.config.auth ++ "/api/v1/auth/google"}>
    {ReasonReact.string("Login with Google")}
  </a>
};