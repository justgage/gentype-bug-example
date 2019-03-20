let whitespaceRegex = Js.Re.fromString("\\s+");

module Block = (BlockDef: {let block: string;}) => {
  open BlockDef;

  let block = block;

  let el = element => block ++ "__" ++ element;

  let addClass = (base, extraClass) => base ++ " " ++ extraClass;

  exception UnableToModifyBlankClassName;

  let modif = (existing: string, modifier: string, cond: bool) =>
    if (cond) {
      let splitOnWhitespace = Js.String.splitByRe(whitespaceRegex);
      let classNames = existing |> splitOnWhitespace |> Array.to_list;

      let (root: string, rest: string) =
        switch (classNames) {
        | [Some(root), ...rest] => (
            root,
            Js.String.concatMany(
              rest
              ->Belt.List.map(x => Belt.Option.getWithDefault(x, ""))
              ->Belt.List.toArray,
              " ",
            ),
          )
        | _ => raise(UnableToModifyBlankClassName)
        };
      let prefix = rest == "" ? root : {j|$root $rest|j};

      {j|$prefix $root--$modifier|j};
    } else {
      existing;
    };
};

/**

Defines a new BEM block that contains functions that allow you to do things like this:

*/;