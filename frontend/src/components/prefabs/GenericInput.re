type state = {
  internalValue: string,
  contentRef: ref(option(Dom.element)),
};

type action =
  | UpdateInternal(string);

module Handlers = {
  let onTextChange = Debouncer.make(~wait=100, fn => fn());
};

let setContentRef = (r, {ReasonReact.state}) =>
  state.contentRef := Js.Nullable.toOption(r);

let setElementContents = (element, isTextArea) => {
  let node = ReactDOMRe.domElementToObj(element);
  ignore(node##focus());
  /* uncertain about this */
  ignore(node##setSelectionRange(node##value##length, node##value##length));
  ();
};

let editableTextAreaStyle = ReactDOMRe.Style.make(~width="100%", ());

let enterSubmitWithCommand = (submitFun, characterFunc, event): Js.Promise.t('a) =>
  if (ReactEvent.Keyboard.keyCode(event) == 13) {
    ReactEvent.Keyboard.preventDefault(event);
    submitFun();
  } else {
    characterFunc();
  };

[@react.component]
let make =
  (
    ~style=?,
    ~className=?,
    ~value,
    ~onTextChange,
    ~isTextArea,
    ~onKeyDown=?,
    ~placeholder,
    ~onBlur=?,
    ~autoFocus=?,
  ) => {

  let (state, dispatch) =
    ReactUpdate.useReducer(
      {contentRef: ref(None), internalValue: value},
      (action, state) =>
        switch (action) {
        | UpdateInternal(internalValue) => ReactUpdate.UpdateWithSideEffects(
            {...state, internalValue},
            (_) => {
              Handlers.onTextChange(() => { onTextChange(internalValue) |> ignore })
              |> ignore;
              None;
            }
        )
      }
    );

  React.useEffect1(() => {
    /* Once */
    switch (state.contentRef^) {
    | Some(field) => setElementContents(field, isTextArea)
    | _ => ()
    };
    None; /* May need a cleanup function */
  }, [||]);
  
  let computedStyle = Utils.Dom.combineStyles(style, editableTextAreaStyle);
  let onChange = event =>
    event
    |> ReactEventRe.Form.target
    |> ReactDOMRe.domElementToObj
    |> (domObject => dispatch(UpdateInternal(domObject##value)));

  let ref = React.useRef(Js.Nullable.null);

  let onKeydownOptional =
    Belt.Option.map(
      onKeyDown,
      (keydownFn, event) => {
        ReactEventRe.Synthetic.persist(event);
        Handlers.onTextChange(() =>
          onTextChange(state.internalValue)
          |> Js.Promise.then_(_ => keydownFn(event))
          |> ignore
        );
      },
    );

  isTextArea ?
    <textarea
      ?className
      style=computedStyle
      ref={ReactDOMRe.Ref.domRef(ref)} 
      onKeyDown=?onKeydownOptional
      placeholder
      onChange
      ?onBlur
      autoFocus={Belt.Option.getWithDefault(autoFocus, false)}
      value={state.internalValue}
    /> :
    <input
      ?className
      style=computedStyle
      ref={ReactDOMRe.Ref.domRef(ref)} 
      onKeyDown=?onKeydownOptional
      placeholder
      onChange
      ?onBlur
      autoFocus={Belt.Option.getWithDefault(autoFocus, false)}
      value={state.internalValue}
    />;
};