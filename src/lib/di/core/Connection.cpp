//---------------------------------------------------------------------------------------
//
// Project: DirectionalityIndicator
//
// Copyright 2014-2015 Sebastian Eichelbaum (http://www.sebastian-eichelbaum.de)
//           2014-2015 Max Planck Research Group "Neuroanatomy and Connectivity"
//
// This file is part of DirectionalityIndicator.
//
// DirectionalityIndicator is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DirectionalityIndicator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DirectionalityIndicator. If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------------------

#include <string>
#include <sstream>

#include "Connection.h"

namespace di
{
    namespace core
    {
        Connection::Connection( ConstSPtr< ConnectorBase > from, SPtr< ConnectorBase > to ):
            m_source( from ),
            m_target( to )
        {
        }

        Connection::~Connection()
        {
        }


        ConstSPtr< ConnectorBase > Connection::getSource() const
        {
            return m_source;
        }

        SPtr< ConnectorBase > Connection::getTarget() const
        {
            return m_target;
        }

        bool Connection::propagate()
        {
            m_packageInfo = "0";

            // only propagate if needed
            if( m_target->getTransferable() != m_source->getTransferable() )
            {
                m_target->setTransferable( m_source->getTransferable() );

                // Also store some info for debugging
                std::stringstream ss;
                ss << static_cast< const void* >( m_source->getTransferable().get() );
                m_packageInfo = ss.str();
                return true;
            }
            return false;
        }

        std::ostream& operator<<( std::ostream& os, const Connection& obj )
        {
            os << obj.getSource()->getName() << std::string( " --(" ) << obj.m_packageInfo << std::string( ")--> " ) << obj.getTarget()->getName();
            return os;
        }
    }
}

