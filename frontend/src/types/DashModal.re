type t =
  | SaveCube
  | ClientDraftCube(Cube_Model.M.idType, ClientDraftPhase.t);

type action =
  | OpenModal(t)
  | CloseModal;