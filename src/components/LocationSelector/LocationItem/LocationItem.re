open Location;

let handleClick = (appendLocation, location) => appendLocation(location);

let component = ReasonReact.statelessComponent("LocationItem");

let make = (~appendLocation, ~location, ~actionButtonsActive, _children) => {
  ...component,
  render: _self => {
    let locationName = location.name |> ReasonReact.string;
    <div onClick={_e => handleClick(appendLocation, location)}>
      <div> <h1> locationName </h1> </div>
      {
        switch (location.address) {
        | Some(address) => <div> address->ReasonReact.string </div>
        | None => ReasonReact.null
        }
      }
    </div>;
  },
};