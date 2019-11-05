
let css = Css.css;
let tw = Css.tw;

type state = int;

type action =
  | AddItems(int);

let addedItems = 12;

let infinteScrollLoadNumbersArea = [%bs.raw {| css(tw`
  flex
  flex-wrap
  overflow-y-scroll
`)|}];

let infinteScrollLoadNumbersButton = [%bs.raw {| css(tw`
  w-full
  flex
  justify-center
  items-center
`)|}];

[@react.component]
let make = (~className: string, ~loader: React.element, ~children: list(React.element)) => {
  let (numItemsState, dispatch) = React.useReducer(
    (numItems, action) =>
      switch (action) {
      | AddItems(num) => min(Belt.List.length(children), numItems + num)
      },
      addedItems
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
      <Button onClick=((_) => dispatch(AddItems(addedItems)))>
        {ReasonReact.string("Add more")}
      </Button>
    </div>
  </div>;
};