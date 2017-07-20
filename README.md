# bs-websockets

WebSockets bindings for BuckleScript.

Available on npm repository: `yarn add bs-websockets` or `npm i -S bs-websockets` to install. Don't forget to add `bs-websockets` to `bs-dependencies` of `bsconfig.json`.

## Example

```reason
open WebSockets
let ws = WebSocket.make webSocketUrl;
let handleOpen () => ...;
let hanhleClose evt /* CloseEvent */ => ...;
let handleMessage evt /* MessageEvent */ => ...;
let handleError errmsg => ...;
ws
  |> WebSocket.setBinaryType ArrayBuffer
  |> WebSocket.on @@ Open handleOpen
  |> WebSocket.on @@ Close handleClose
  |> WebSocket.on @@ Message handleMessage
  |> WebSocket.on @@ Error handleError
  |> ignore;
```
