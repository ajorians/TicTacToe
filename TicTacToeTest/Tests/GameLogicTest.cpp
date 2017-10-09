#include "stdafx.h"
#include <TicTacToeLib/GameLogic.h>
#include <TicTacToeLib/GameBoard.h>

namespace 
{
   class GameLogicTest : public ::testing::Test
   {
   protected:
      GameBoard m_Board{ 3 };
      void SetUp()
      {
         m_Board.ClearBoard();
      }

      void TearDown(){}
   };

   TEST_F( GameLogicTest, PlaceNextPiece_CalledWithSpot_WillPutPieceAtSpot )
   {
      GameLogic logic{ m_Board };

      //Check that spots are empty
      ASSERT_EQ( Empty, m_Board.GetPieceAt( 0, 0 ) );
      ASSERT_EQ( Empty, m_Board.GetPieceAt( 1, 1 ) );
      ASSERT_EQ( Empty, m_Board.GetPieceAt( 2, 2 ) );

      //Make some fake moves
      logic.PlaceNextPiece( 0, 0 );
      logic.PlaceNextPiece( 1, 1 );
      logic.PlaceNextPiece( 2, 2 );

      //Make sure board has those moves
      ASSERT_NE( Empty, m_Board.GetPieceAt( 0, 0 ) );
      ASSERT_NE( Empty, m_Board.GetPieceAt( 1, 1 ) );
      ASSERT_NE( Empty, m_Board.GetPieceAt( 2, 2 ) );
   }

   TEST_F( GameLogicTest, ResetGame_Called_WillResetTheGame )
   {
      GameLogic logic{ m_Board };

      //Make some fake moves
      logic.PlaceNextPiece( 0, 0 );
      logic.PlaceNextPiece( 1, 1 );
      logic.PlaceNextPiece( 2, 2 );

      //Make sure board has those moves
      ASSERT_NE( Empty, m_Board.GetPieceAt( 0, 0 ) );
      ASSERT_NE( Empty, m_Board.GetPieceAt( 1, 1 ) );
      ASSERT_NE( Empty, m_Board.GetPieceAt( 2, 2 ) );

      logic.ResetGame();

      //Check they are now empty
      ASSERT_EQ( Empty, m_Board.GetPieceAt( 0, 0 ) );
      ASSERT_EQ( Empty, m_Board.GetPieceAt( 1, 1 ) );
      ASSERT_EQ( Empty, m_Board.GetPieceAt( 2, 2 ) );
   }

}// namespace
