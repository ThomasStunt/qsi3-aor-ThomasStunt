open Jest;

open Expect;

open Tennis;

describe("Test tennis transitions", () => {
  test("Given deuce when player wins then score is correct", () =>
    expect(scoreWhenDeuce(PlayerOne)) |> toEqual(Advantage(PlayerOne))
  );

  test("Given advantage when advantaged player wins then score is correct", () => {
    let advantagedPlayer = PlayerOne;
    let winner = advantagedPlayer;
    expect(Tennis.scoreWhenAdvantage(advantagedPlayer, winner)) |> toEqual(Game(advantagedPlayer));
  });

  test("Given advantage when the other player wins then score is Deuce", () => {
    let advantagedPlayer = PlayerOne;
    let winner = other(advantagedPlayer);
    expect(Tennis.scoreWhenAdvantage(advantagedPlayer, winner)) |> toEqual(Deuce);
  });

  test("Given player: 40 when wins then score is Game for this player", () => {
    let fortyThirty = {player: PlayerOne, otherPlayerPoint: Thirty};
    expect(scoreWhenForty(fortyThirty, fortyThirty.player)) |> toEqual(Game(fortyThirty.player));
  });

  test("Given player: 40 | other : 30 when other wins then score is Deuce", () => {
    let fortyThirty = {player: PlayerOne, otherPlayerPoint: Thirty};
    expect(scoreWhenForty(fortyThirty, other(fortyThirty.player))) |> toEqual(Deuce);
  });

  test("Given player: 40 | other < 30 when other wins then score is not Deuce", () => {
    let fortyLove = {player: PlayerOne, otherPlayerPoint: Love};
    let fortyFifteen = {player: PlayerOne, otherPlayerPoint: Fifteen};
    expect(scoreWhenForty(fortyLove, other(fortyLove.player))) |> toEqual(Forty(fortyFifteen));
  });

  test("Given player: 15 | other : 15 when player wins then score is 30/15", () => {
    let fifteenFifteen = {playerOne: Fifteen, playerTwo: Fifteen};
    let thirtyFifteen = {playerOne: Thirty, playerTwo: Fifteen};
    expect(scoreWhenPoints(fifteenFifteen, PlayerOne)) |> toEqual(Points(thirtyFifteen));
  });

  test("Given player: 0 | other : 15 when other wins then score is 0/30", () => {
    let loveFifteen = {playerOne: Love, playerTwo: Fifteen};
    let loveThirty = {playerOne: Love, playerTwo: Thirty};
    expect(scoreWhenPoints(loveFifteen, other(PlayerOne))) |> toEqual(Points(loveThirty));
  });

  test("Given player: 30 | other : 15 when player wins then score is 40/15", () => {
    let thirtyFifteen = {playerOne: Thirty, playerTwo: Fifteen};
    let fortyFifteen = {player: PlayerOne, otherPlayerPoint: Fifteen};
    expect(scoreWhenPoints(thirtyFifteen, PlayerOne)) |> toEqual(Forty(fortyFifteen));
  });
});

describe("Test string_of_X", () => {
  test("Given PlayerOne then Player 1:", () => {
    let player = PlayerOne;
    expect(string_of_player(player)) |> toEqual("Player 1:");
  });

  test("Given PlayerTwo then Player 2:", () => {
    let player = PlayerTwo;
    expect(string_of_player(player)) |> toEqual("Player 2:");
  });

  test("Given Love then 0", () => {
    let lve = Love;
    expect(string_of_point(lve)) |> toEqual("0");
  });

  test("Given Fifteen then 15", () => {
    let fteen = Fifteen;
    expect(string_of_point(fteen)) |> toEqual("15");
  });

  test("Given Thirty then 30", () => {
    let thty = Thirty;
    expect(string_of_point(thty)) |> toEqual("30");
  });

  test("Given 30 - 15, then Player 1:30 - Player 2:15", () => {
    let score = Points({playerOne: Thirty, playerTwo: Fifteen});
    expect(string_of_score(score)) |> toEqual("Player 1:30 - Player 2:15");
  });

  test("Given 40 - 15, then Player 1:40 - Player 2:15", () => {
    let fortyFifteen = Forty({player: PlayerOne, otherPlayerPoint: Fifteen});
    expect(string_of_score(fortyFifteen)) |> toEqual("Player 1:40 - Player 2:15");
  });

  test("Given 15 - 40, then Player 1:15 - Player 2:40", () => {
    let fifteenForty = Forty({player: PlayerTwo, otherPlayerPoint: Fifteen});
    expect(string_of_score(fifteenForty)) |> toEqual("Player 1:15 - Player 2:40");
  });

  test("Given Deuce, then Player 1:40 - Player 2:40", () => {
    let deuce = Deuce;
    expect(string_of_score(deuce)) |> toEqual("Player 1:40 - Player 2:40");
  });

  test("Given AD - 40, then Player 1:AD - Player 2:40", () => {
    let adv = Advantage(PlayerOne);
    expect(string_of_score(adv)) |> toEqual("Player 1:AD - Player 2:40");
  });

  test("Given 40 - AD, then Player 1:40 - Player 2:AD", () => {
    let adv = Advantage(PlayerTwo);
    expect(string_of_score(adv)) |> toEqual("Player 1:40 - Player 2:AD");
  });

  test("Given Game to PlayerOne", () => {
    let g1 = Game(PlayerOne);
    expect(string_of_score(g1)) |> toEqual("Player 1:WIN");
  });
});
