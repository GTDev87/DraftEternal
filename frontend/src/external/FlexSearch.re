type index;

[@bs.val] [@bs.module "flexsearch"] external create: unit => index  = "create";

[@bs.send] external addValue: (index, string, string) => index = "add";
[@bs.send] external search: (index, string) => array(string) = "search";