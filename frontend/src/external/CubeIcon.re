[@bs.obj]
external makeProps: (~style: string=?, unit) => {. "style": string} = "";

[@bs.module "react-icons/fa"]
external make: ({. "style": string}) => React.element = "FaCube";