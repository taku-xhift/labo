/**
 * @file
 * @brief 外部呼出し用モジュール。
 * @note    これを Perl なりで呼び出してもらうと、
 *              一通りの作業が c++ で行われる。
*/

#ifndef CINTERFACE_LEAGUEMODE_HPP_INCLUDED
#define CINTERFACE_LEAGUEMODE_HPP_INCLUDED

//-----------------------------------------------------
//  include
//-----------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif


/**----------------------------------------------------
 * @brief LeagueMode → チームセレクトに関する処理担当
 *----------------------------------------------------*/
void LeagueMode_TeamSelect();



/**----------------------------------------------------
 * @brief LeagueMode → 試合結果の出力に関する処理担当
 *----------------------------------------------------*/
void LeagueMode_AutoGame(const char* homeTeam_, const char* awayTeam_);



#ifdef __cplusplus
}
#endif


#endif

