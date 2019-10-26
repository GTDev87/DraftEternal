/*[@bs.module "skatejs"] external withComponent : 'a => 'a = "withComponent";
[@bs.module "@skatejs/renderer-react"] external wrap: 'a => 'a = "wrap"; 


let statelessComponent = (name) => {

  Js.log("prev comp.reactClassInternal");
  Js.log(comp.reactClassInternal);

  let res =
    Document.isBrowser()
    ? {
        ...comp,
        reactClassInternal:
          (
            comp.reactClassInternal
            |> (a) => {
                 Js.log("a");
                 Js.log("wrap");
                 Js.log(wrap);
                 [%debugger];
                 Js.log(a); wrap(a);
               }
            |> (b) => {Js.log("b"); Js.log(b); withComponent(b);}
          )
      }
    : comp;

  Js.log("post res.reactClassInternal");
  Js.log(res.reactClassInternal);

  Js.log("res");
  Js.log(res);

  res;
};

*/