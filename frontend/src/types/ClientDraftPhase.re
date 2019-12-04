type t =
  | Start
  | Choice(ClientDraft.t, int)
  | End;