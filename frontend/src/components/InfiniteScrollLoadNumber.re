
let css = Css.css;
let tw = Css.tw;

type state = int;

type action =
  | AddItems(int);

let addedItems = 24;
let startItems = 48;

let infinteScrollLoadNumbersArea = [%bs.raw {| css(tw`
  flex
  flex-wrap
  overflow-y-scroll
  h-full
`)|}];

let infinteScrollLoadNumbersButton = [%bs.raw {| css(tw`
  p-2
`)|}];


[@react.component]
let make = (~className: string, ~loader: React.element, ~children: list(React.element)) => {
  let (numItemsState, dispatch) = React.useReducer(
    (numItems, action) =>
      switch (action) {
      | AddItems(num) => min(Belt.List.length(children), numItems + num)
      },
      startItems
  );
  <div className>
    <div className=infinteScrollLoadNumbersArea>
      {
        children
        |> Belt.List.take(_, numItemsState)
        |> (oItems) =>
            switch(oItems){
            | None => children |> Utils.ReasonReact.listToReactArray
            | Some(items) => items |> Utils.ReasonReact.listToReactArray
            }
      }
      {
        numItemsState < Belt.List.length(children) ?
          <Button autoFocus=false className=infinteScrollLoadNumbersButton onClick=((_) => dispatch(AddItems(addedItems)))>
            {ReasonReact.string("more...")}
          </Button> :
          <div/>
      }
    </div>
  </div>;
};