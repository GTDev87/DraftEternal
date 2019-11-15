type obj = {. "style": string, "className": string};

[@bs.obj]
external makeProps: (~style: string=?, ~className: string=?, unit) => obj = "";

[@bs.module "react-icons/fa"]
external make: (obj) => React.element = "FaCube";