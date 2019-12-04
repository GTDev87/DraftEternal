module type Type = {
  type _data;
  let _defaultData: (string) => _data;
}

module Type = {
  type t('model, 'local) = {
    data: 'model,
    local: 'local,
  };
  
  type _data;
}
