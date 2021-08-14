/**
 * @file
 * @brief �O���ďo���p���W���[���B
 * @note    ����� Perl �Ȃ�ŌĂяo���Ă��炤�ƁA
 *              ��ʂ�̍�Ƃ� c++ �ōs����B
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
 * @brief LeagueMode �� �`�[���Z���N�g�Ɋւ��鏈���S��
 *----------------------------------------------------*/
void LeagueMode_TeamSelect();



/**----------------------------------------------------
 * @brief LeagueMode �� �������ʂ̏o�͂Ɋւ��鏈���S��
 *----------------------------------------------------*/
void LeagueMode_AutoGame(const char* homeTeam_, const char* awayTeam_);



#ifdef __cplusplus
}
#endif


#endif

