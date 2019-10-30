let component = ReasonReact.statelessComponent("NewTypeModalContents");

[@react.component]
let make =
    (
      ~titleText,
      ~descriptionText,
      ~buttonText,
      ~addType,
      ~placeholderText,
      ~value,
      ~onChange,
      ~onKeyDown,
      ~children,
    ) => {
    <div/>
    // <NewTypeModalContentLayout titleText descriptionText buttonText addType>
    //   <TextInput
    //     style=inputStyle
    //     placeholder=placeholderText
    //     value
    //     onTextChange={a => onChange(a)}
    //     onKeyDown
    //     autoFocus=true
    //   />
    // </NewTypeModalContentLayout>
};