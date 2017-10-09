#include "stdafx.h"
#include <afx.h> // Only to turn off MFC's false leak detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <objbase.h>
#include <fstream>

#include <TestHelpers/TaskbarFeatureListener.h>

class COMInitialization
{
public:
   COMInitialization()
   {
      CoInitialize( NULL );
   }
   ~COMInitialization()
   {
      CoUninitialize();
   }
};

int _tmain( int argc, _TCHAR* argv[] )
{
   AfxEnableMemoryTracking( FALSE );

   ::testing::FLAGS_gmock_verbose = NEVER_TRANSLATEA( "error" );
   //::testing::FLAGS_gmock_verbose = "info";
   //::testing::FLAGS_gmock_verbose = "warning";
   ::testing::FLAGS_gtest_filter = NEVER_TRANSLATEA( "*" );
   ::testing::FLAGS_gtest_print_time = NEVER_TRANSLATEA( "1" );
   ::testing::FLAGS_gtest_catch_exceptions = 0;

   std::ifstream flagsfile;

   flagsfile.open( NEVER_TRANSLATEA( "gtest_flags" ) );
   if ( flagsfile.is_open() )
   {
      std::string temp;

      getline( flagsfile, temp );
      if ( !flagsfile.fail() )
         ::testing::FLAGS_gmock_verbose = temp;

      getline( flagsfile, temp );
      if ( !flagsfile.fail() )
         ::testing::FLAGS_gtest_filter = temp;
   }
   flagsfile.close();

   ::testing::InitGoogleTest( &argc, argv );
   ::testing::InitGoogleMock( &argc, argv );

   _CrtMemState memState;
   UNUSED( memState ); // fix warning for Release build
   _CrtMemCheckpoint( &memState );

   COMInitialization com;

#ifndef NO_TASKBAR_PROGRESS
   TaskbarFeatureListener taskbarProgress;
   ::testing::UnitTest::GetInstance()->listeners().Append( &taskbarProgress );
#endif

   int result = RUN_ALL_TESTS();

#ifndef NO_TASKBAR_PROGRESS
   ::testing::UnitTest::GetInstance()->listeners().Release( &taskbarProgress );
#endif

#ifdef _DEBUG
   OutputDebugString( NEVER_TRANSLATEL( "*** Dumping any leaked objects ***\n" ) );
#endif
   _CrtMemDumpAllObjectsSince( &memState );

#ifdef _DEBUG
   std::cout << NEVER_TRANSLATEA( "\nPress enter to continue..." );
   std::cin.get();
   OutputDebugString( NEVER_TRANSLATEL( "*** Ignore all leaks below this line, they are false positives ***\n" ) );
#endif

   return result;
}

