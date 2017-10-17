#include <QString>
#include <QStringList>

#include "GameProtocol.h"

namespace Game
{
    namespace Protocol
    {
        class GameProtocol::Impl
        {
        public:
            struct PointResolutionData
            {
                bool m_ok;
                Model::Point m_point;
            };

            Impl()
            {
            }

            ~Impl()
            {
            }

            GameActionType ResolveActionTypeBasedOnLetter(const QChar& character) const
            {
                if (character == 'M')
                    return GameActionType::Move;
                else if (character == 'A')
                    return GameActionType::Attack;

                return GameActionType::Unknown;
            }

            PointResolutionData ResolvePoint(const QString& pointRaw) const
            {
                PointResolutionData data;
                data.m_ok = false;

                const auto points = pointRaw.split(",");
                if (points.size() != 2)
                    return data;

                unsigned int x = points[0].toUInt(&data.m_ok);
                if (!data.m_ok)
                    return data;

                unsigned int y = points[1].toUInt(&data.m_ok);
                if (!data.m_ok)
                    return data;

                data.m_point = Game::Model::Point(x, y);
                return data;
            }
        };

        GameProtocol::GameProtocol()
            : m_impl(new Impl())
        {
        }

        GameProtocol::~GameProtocol()
        {
        }

        std::vector<GameAction> GameProtocol::ResolveActions(const std::string& data) const
        {
            if (data.empty())
                return {};

            std::vector<GameAction> actions;
            QString qData = QString::fromStdString(data);
            if (!qData.contains("\n"))
                return {};

            for (const auto& element : qData.split("\n"))
            {
                const auto elementTrimmed = element.trimmed();
                if (elementTrimmed.length() == 0)
                    continue;

                GameAction action;
                action.m_type = m_impl->ResolveActionTypeBasedOnLetter(elementTrimmed.at(0));
                if (action.m_type == GameActionType::Unknown)
                    continue; // Unrecognized action. Ignore.

                const auto elementActionParsed = elementTrimmed.mid(1);

                // TODO: This can be refactored for the better.
                if (elementActionParsed.contains(";"))
                {
                    const auto elements = elementActionParsed.split(";");
                    const auto resolutionDataOne = m_impl->ResolvePoint(elements[0]);
                    if (!resolutionDataOne.m_ok)
                        continue;

                    action.m_activator = resolutionDataOne.m_point;

                    const auto resolutionDataTwo = m_impl->ResolvePoint(elements[1]);
                    if (!resolutionDataTwo.m_ok)
                        continue;
                    action.m_affected = resolutionDataTwo.m_point;
                }
                else
                {
                    const auto resolutionData = m_impl->ResolvePoint(elementActionParsed);
                    if (!resolutionData.m_ok)
                        continue;

                    action.m_activator = resolutionData.m_point;
                    action.m_affected = resolutionData.m_point;
                }

                actions.push_back(action);
            }
            return actions;
        }
    }
}
