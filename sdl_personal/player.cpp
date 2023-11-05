#include "player.hpp"

Player::Player(MazeRoom* pRoom, string roomIdentifier, string playerIdentifier) {
    m_pRoom = pRoom;
    m_roomIdentifier = roomIdentifier;
    m_playerIdentfier = playerIdentifier;
}


void Player::move(Dirs dir) {
    switch(dir) {
        case Dirs::north:
            if (m_pRoom->getRoom(Dirs::north) != nullptr) {
                m_pRoom->updateIdentifier(m_roomIdentifier);
                m_pRoom = m_pRoom->getRoom(Dirs::north);
                m_pRoom->updateIdentifier(m_playerIdentfier);
            }
            return;
        case Dirs::south:
            if (m_pRoom->getRoom(Dirs::south) != nullptr) {
                m_pRoom->updateIdentifier(m_roomIdentifier);
                m_pRoom = m_pRoom->getRoom(Dirs::south);
                m_pRoom->updateIdentifier(m_playerIdentfier);
            }
            return;
        case Dirs::east:
            if (m_pRoom->getRoom(Dirs::east) != nullptr) {
                m_pRoom->updateIdentifier(m_roomIdentifier);
                m_pRoom = m_pRoom->getRoom(Dirs::east);
                m_pRoom->updateIdentifier(m_playerIdentfier);
            }
            return;
        case Dirs::west:
            if (m_pRoom->getRoom(Dirs::west) != nullptr) {
                m_pRoom->updateIdentifier(m_roomIdentifier);
                m_pRoom = m_pRoom->getRoom(Dirs::west);
                m_pRoom->updateIdentifier(m_playerIdentfier);
            }
        default:
            return;
    };
};

