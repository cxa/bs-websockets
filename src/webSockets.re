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
  let makeWithProtocol ::url protocol::(p: string) => _make url @@ Js.Null_undefined.return p;
  let makeWithProtocols ::url protocols::(ps: list string) =>
    _make url (Js.Null_undefined.return @@ Array.of_list ps);
  type binaryType =
    | Blob
    | ArrayBuffer;
  external _binaryType : t => string = "binaryType" [@@bs.get];
  external _setBinaryType : t => string => unit = "binaryType" [@@bs.set];
  let binaryType t => {
    let str = _binaryType t;
    str == "blob" ? Blob : ArrayBuffer
  };
  let setBinaryType t binaryType => {
    let str =
      switch binaryType {
      | Blob => "blob"
      | ArrayBuffer => "arraybuffer"
      };
    _setBinaryType t str
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
