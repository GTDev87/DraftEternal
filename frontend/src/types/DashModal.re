type t =
  | SaveCube;

type action =
  | OpenModal(t)
  | CloseModal;