// type state = {
//   internalValue: string,
//   contentRef: ref(option(Dom.element)),
// };

// type action =
//   | UpdateInternal(string)
//   | Nothing;

// module Handlers = {
//   let onTextChange = Debouncer.make(~wait=200, fn => fn());
// };

// let component = ReasonReact.reducerComponent("GenericInput");

// let setContentRef = (r, {ReasonReact.state}) =>
//   state.contentRef := Js.Nullable.toOption(r);

// let setElementContents = (element, isTextArea) => {
//   let node = ReactDOMRe.domElementToObj(element);
//   ignore(node##focus());
//   /* uncertain about this */
//   ignore(node##setSelectionRange(node##value##length, node##value##length));
//   ();
// };

// let editableTextAreaStyle = ReactDOMRe.Style.make(~width="100%", ());

// let enterSubmitWithCommand = (submitFun, characterFunc, event): Js.Promise.t('a) =>
//   if (ReactEvent.Keyboard.keyCode(event) == 13) {
//     ReactEvent.Keyboard.preventDefault(event);
//     submitFun();
//   } else {
//     characterFunc();
//   };

// [@react.component]
// let make =
//   (
//     ~style=?,
//     ~className=?,
//     ~value,
//     ~onTextChange,
//     ~isTextArea,
//     ~onKeyDown=?,
//     ~placeholder,
//     ~onBlur=?,
//     ~autoFocus=?,
//     _children,
//   ) => {
// initialState: () => {contentRef: ref(None), internalValue: value},
// reducer: (_action, state) =>
//   switch (_action) {
//   | UpdateInternal(internalValue) =>
//     ReasonReact.UpdateWithSideEffects(
//       {...state, internalValue},
//       (
//         _ =>
//           Handlers.onTextChange(() => onTextChange(internalValue) |> ignore)
//       ),
//     )
//   | Nothing => ReasonReact.NoUpdate
//   },
// didMount: self =>
//   switch (self.state.contentRef^) {
//   | Some(field) => setElementContents(field, isTextArea)
//   | _ => ()
//   },
// render: self => {
//   let computedStyle = Utils.Dom.combineStyles(style, editableTextAreaStyle);
//   let onChange = event =>
//     event
//     |> ReactEventRe.Form.target
//     |> ReactDOMRe.domElementToObj
//     |> (domObject => self.send(UpdateInternal(domObject##value)));

//   let ref = self.handle(setContentRef);

//   let onKeydownOptional =
//     Belt.Option.map(
//       onKeyDown,
//       (keydownFn, event) => {
//         ReactEventRe.Synthetic.persist(event);
//         Handlers.onTextChange(() =>
//           onTextChange(self.state.internalValue)
//           |> Js.Promise.then_(_ => keydownFn(event))
//           |> ignore
//         );
//       },
//     );

//   isTextArea ?
//     <textarea
//       ?className
//       style=computedStyle
//       ref
//       onKeyDown=?onKeydownOptional
//       placeholder
//       onChange
//       ?onBlur
//       autoFocus={Belt.Option.getWithDefault(autoFocus, false)}
//       value={self.state.internalValue}
//     /> :
//     <input
//       ?className
//       style=computedStyle
//       ref
//       onKeyDown=?onKeydownOptional
//       placeholder
//       onChange
//       ?onBlur
//       autoFocus={Belt.Option.getWithDefault(autoFocus, false)}
//       value={self.state.internalValue}
//     />;
//   },
// };