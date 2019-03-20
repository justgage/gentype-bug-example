[@genType]
type locations = array(Location.location);

let component = ReasonReact.statelessComponent("LocationsList");

[@genType]
let make =
    (
      ~locations: locations,
      ~isLoading: bool,
      ~appendLocation,
      ~selectedLocation: option(Location.location),
      _children,
    ) => {
  ...component,
  render: _self => {
    let isNoLocations = Array.length(locations) == 0;

    <div>
      {
        if (isLoading) {
          <div> <div /> </div>;
        } else {
          ReasonReact.null;
        }
      }
      {
        if (!isLoading && !isNoLocations) {
          <div>
            {
              Array.map(
                location => {
                  let actionButtonsActive =
                    switch (selectedLocation) {
                    | Some(selectedLocation) => selectedLocation == location
                    | None => false
                    };
                  <LocationItem
                    key={location.id}
                    location
                    appendLocation
                    actionButtonsActive
                  />;
                },
                locations,
              )
              |> ReasonReact.array
            }
          </div>;
        } else {
          ReasonReact.null;
        }
      }
      {
        if (!isLoading && isNoLocations) {
          <div>
            <div> "No location matching your search"->ReasonReact.string </div>
          </div>;
        } else {
          ReasonReact.null;
        }
      }
    </div>;
  },
};