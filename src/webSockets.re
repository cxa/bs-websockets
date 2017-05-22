module MessageEvent = {
  type t;
  external t : t = "MessageEvent" [@@bs.new];
  external data : t => Js.t 'a = "" [@@bs.get];
  external origin : t => string = "" [@@bs.get];
  external lastEventId : t => string = "" [@@bs.get];
  external source : t => Js.t {..} = "" [@@bs.get];
  external ports : t => array (Js.t {..}) = "" [@@bs.get];
};

module CloseEvent = {
  type t;
  external t : t = "CloseEvent" [@@bs.new];
  external code : t => int = "" [@@bs.get];
  external reason : t => string = "" [@@bs.get];
  external wasClean : t => bool = "" [@@bs.get];
};

module WebSocket = {
  type t;
  external _make : string => Js.Null_undefined.t 'a => t = "WebSocket" [@@bs.new];
  let make ::url => _make url Js.Null_undefined.null;
  let make_with_protocol ::url protocol::(p: string) => _make url @@ Js.Null_undefined.return p;
  let make_with_protocols ::url protocols::(ps: list string) =>
    _make url (Js.Null_undefined.return @@ Array.of_list ps);
  type binaryType =
    | Blob
    | ArrayBuffer;
  external _get_binary_type : t => string = "binaryType" [@@bs.get];
  external _set_binary_type : t => string => unit = "binaryType" [@@bs.set];
  let get_binary_type t => {
    let str = _get_binary_type t;
    str == "blob" ? Blob : ArrayBuffer
  };
  let set_binary_type t binaryType => {
    let str =
      switch binaryType {
      | Blob => "blob"
      | ArrayBuffer => "arraybuffer"
      };
    _set_binary_type t str
  };
  external bufferedAmount : t => int64 = "" [@@bs.get];
  external extensions : t => Js.t 'a = "" [@@bs.get];
  external onclose : t => (CloseEvent.t => unit) => unit = "" [@@bs.send.pipe : t];
  external onerror : t => (Js.t {..} => unit) => unit = "" [@@bs.send.pipe : t];
  external onmessage : t => (MessageEvent.t => unit) => unit = "" [@@bs.send.pipe : t];
  external onopen : t => (Js.t {..} => unit) => unit = "" [@@bs.send.pipe : t];
  external protocol : t => string = "" [@@bs.get];
  external readyState : t => int32 = "" [@@bs.get];
  external url : t => string = "" [@@bs.get];
};
