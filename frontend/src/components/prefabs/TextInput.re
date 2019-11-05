[@react.component]
let make =
    (
      ~style=?,
      ~className=?,
      ~value,
      ~onTextChange,
      ~onKeyDown=?,
      ~placeholder,
      ~onBlur=?,
      ~autoFocus=?,
    ) => {
  <GenericInput
    isTextArea=false
    ?className
    ?style
    value
    onTextChange
    ?onKeyDown
    placeholder
    ?onBlur
    ?autoFocus
  />
};