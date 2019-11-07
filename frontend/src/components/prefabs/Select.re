type selectionType('a) = {
  id: 'a,
  text: string,
};

type selections('a) = list(selectionType('a));
type idToString('a) = 'a => string;

let selectStyle =
  ReactDOMRe.Style.make(
    ~padding="0.0em 2.5em 0.0em .5em",
    ~backgroundSize="5px 5px, 5px 5px, 1px 1.0em",
    ~backgroundRepeat="no-repeat",
    ~borderRadius="0",
    (),
  );

let stringToId =
    (selections: selections('a), idToString: idToString('a), s: string)
    : option('a) =>
  selections
  |> Belt.List.getBy(_, (selection: selectionType('a)) => idToString(selection.id) == s)
  |> Belt.Option.map(_, s => s.id);

[@react.component]
let make =
  (
    ~selectedId: 'a,
    ~selections: selections('a),
    ~idToString,
    ~onSelect: option('a) => 'b,
  ) => {
  let partialStringToId = stringToId(selections, idToString);
  let valueSelectTest =
    Utils.Dom.getValueDoAction(a => a |> partialStringToId |> onSelect);

  <select
    style=selectStyle
    value={selectedId |> idToString}
    onChange=valueSelectTest
  >
    {
      selections
      |> Belt.List.map(_, s =>
            <option key={s.id |> idToString} value={s.id |> idToString}>
              {ReasonReact.string(s.text)}
            </option>
          )
      |> Utils.ReasonReact.listToReactArray
    }
  </select>;
};