let randomString: unit => string = [%raw
  () => "return (Math.random().toString(36).replace(/[^a-z]+/g, '').substr(2, 10) || '') + 'g';"
];