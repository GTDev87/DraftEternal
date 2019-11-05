// InfiniteScroll
// type obj = {.
//   "className": string,
//   "pageStart": int,
//   "loadMore": unit => unit,
//   "hasMore": bool,
//   "loader": React.element,
//   "children": React.element
// };

// [@bs.obj]
// external makeProps: (
//   ~pageStart: int,
//   ~loadMore: unit => unit,
//   ~hasMore: bool,
//   ~loader: React.element,
//   ~children: React.element,
//   unit
// ) => obj = "";

[@bs.module "react-infinite-scroller"] [@react.component]
external make: (
  ~className: string,
  ~pageStart: int,
  ~loadMore: unit => unit,
  ~hasMore: bool,
  ~loader: React.element,
  ~dataLength: int,
  ~children: React.element,
  unit
) => React.element = "default";
