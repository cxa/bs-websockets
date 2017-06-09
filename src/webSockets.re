module MessageEvent = {
  type t;
  external data : t => 'a = "" [@@bs.get];
  external arrayBufferData : t => Js.Typed_array.array_buffer = "data" [@@bs.get];
  external stringData : t => string = "data" [@@bs.get];
  external origin : t => string = "" [@@bs.get];
  external lastEventId : t => string = "" [@@bs.get];
  external source : t => Js.t {..} = "" [@@bs.get];
  external ports : t => array (Js.t {..}) = "" [@@bs.get];
};

module CloseEvent = {
  type t;
  external code : t => int = "" [@@bs.get];
  external reason : t => string = "" [@@bs.get];
  external wasClean : t => bool = "" [@@bs.get];
};

module type WebSocketMaker = {
  type t;
  let make: string => t;
  let makeWithProtocols: string => protocols::'a => t;
};

module MakeWebSocket (Maker: WebSocketMaker) => {
  type t = Maker.t;
  let make = Maker.make;
  let makeWithProtocol url protocol::(p: string) => Maker.makeWithProtocols url protocols::p;
  let makeWithProtocols url protocols::(ps: list string) =>
    Maker.makeWithProtocols url protocols::(Array.of_list ps);
  type binaryType =
    | Blob
    | ArrayBuffer;
  external _binaryType : t => string = "binaryType" [@@bs.get];
  external _setBinaryType : t => string => unit = "binaryType" [@@bs.set];
  let binaryType t => {
    let str = _binaryType t;
    str == "blob" ? Blob : ArrayBuffer
  };
  let setBinaryType binaryType t => {
    let typestr =
      binaryType |> (
        fun
        | Blob => "blob"
        | ArrayBuffer => "arraybuffer"
      );
    _setBinaryType t typestr;
    t
  };
  external bufferedAmount : t => int64 = "" [@@bs.get];
  external extensions : t => 'a = "" [@@bs.get];
  type event =
    | Close (CloseEvent.t => unit)
    | Error (string => unit)
    | Message (MessageEvent.t => unit)
    | Open (unit => unit);
  external _on : string => (Js.t {..} => unit) => unit = "addEventListener" [@@bs.send.pipe : t];
  let on e t => {
    let evtname =
      switch e {
      | Close _ => "close"
      | Error _ => "error"
      | Message _ => "message"
      | Open _ => "open"
      };
    _on
      evtname
      (
        fun jsobj =>
          switch e {
          | Close fn => fn @@ Obj.magic jsobj
          | Error fn => fn jsobj##message
          | Message fn => fn @@ Obj.magic jsobj
          | Open fn => fn ()
          }
      )
      t;
    t
  };
  external protocol : t => string = "" [@@bs.get];
  type readyState =
    | Connecting
    | Open
    | Closing
    | Closed;
  external _readyState : t => int = "readyState" [@@bs.get];
  let readyState t =>
    switch (_readyState t) {
    | 0 => Connecting
    | 1 => Open
    | 2 => Closing
    | _ => Closed
    };
  external url : t => string = "" [@@bs.get];
  external close : unit => unit = "" [@@bs.send.pipe : t];
  external closeWithCode : int => unit = "close" [@@bs.send.pipe : t];
  external closeWithReason : string => unit = "close" [@@bs.send.pipe : t];
  external closeWithCodeAndReason : int => string => unit = "close" [@@bs.send.pipe : t];
  external sendString : string => unit = "send" [@@bs.send.pipe : t];
  external sendArrayBuffer : Js.Typed_array.array_buffer => unit = "send" [@@bs.send.pipe : t];
  type blob;
  external sendBlob : blob => unit = "send" [@@bs.send.pipe : t];
};

module BrowserWebSocket = {
  type t;
  external make : string => t = "WebSocket" [@@bs.new];
  external makeWithProtocols : string => protocols::'a => t = "WebSocket" [@@bs.new];
};

module WebSocket = MakeWebSocket BrowserWebSocket;
/** Tips: If you need to make a WebSocket client on Nodejs, you can make a module to implement WebSocketMaker as BrowserWebSocket. e.g.
  *
  * WARNING: It's an untested example.
  *
 module WSWebSocket = {
   type t;
   external make : string => t = "WebSocket" [@@bs.new] [@@bs.module "ws"];
   external makeWithProtocols : string => protocols::'a => t =
     "WebSocket" [@@bs.new] [@@bs.module "ws"];
 };

 module NodeWSClient = MakeWebSocket WSWebSocket;
 *
 */
