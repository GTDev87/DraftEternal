type t = {
  cubeId: Cube_Model.M.idType,
  seed: UUID.t,
  packSize: int,
  numDrafters: int,
  picks: list(list(Card_Model.M.idType)),
  packs: list(list(Card_Model.M.idType)),
};