/*
 * (c) Copyright Ascensio System SIA 2010-2019
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-12 Ernesta Birznieka-Upisha
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#pragma once
#include "TextCFException.h"
#include "TextPFException.h"


namespace PPT_FORMAT
{

struct STextMasterStyleLevel
{
    nullable<USHORT> m_level;
    STextPFException m_pf;
    STextCFException m_cf;


    void ReadFromStream(POLE::Stream* pStream, bool hasLevelField)
    {
        if (hasLevelField)
            m_level = new USHORT(StreamUtils::ReadWORD(pStream));
        m_pf.ReadFromStream(pStream);
        m_cf.ReadFromStream(pStream);
    }
};

class CRecordTextMasterStyleAtom : public CUnknownRecord
{
public:
    USHORT m_cLevels;

    nullable<STextMasterStyleLevel> m_lstLvl1;
    nullable<STextMasterStyleLevel> m_lstLvl2;
    nullable<STextMasterStyleLevel> m_lstLvl3;
    nullable<STextMasterStyleLevel> m_lstLvl4;
    nullable<STextMasterStyleLevel> m_lstLvl5;

    void ReadFromStream(SRecordHeader &oHeader, POLE::Stream *pStream) override
    {
        m_oHeader = oHeader;
        LONG lPos; StreamUtils::StreamPosition(lPos, pStream);


        m_cLevels = StreamUtils::ReadWORD(pStream);
        if (m_cLevels > 0)
        {
            m_lstLvl1 = new STextMasterStyleLevel;
            m_lstLvl1->ReadFromStream(pStream, m_oHeader.RecInstance >= 5);
            if (m_cLevels > 1)
            {
                m_lstLvl2 = new STextMasterStyleLevel;
                m_lstLvl2->ReadFromStream(pStream, m_oHeader.RecInstance >= 5);
                if (m_cLevels > 2)
                {
                    m_lstLvl3 = new STextMasterStyleLevel;
                    m_lstLvl3->ReadFromStream(pStream, m_oHeader.RecInstance >= 5);
                    if (m_cLevels > 3)
                    {
                        m_lstLvl4 = new STextMasterStyleLevel;
                        m_lstLvl4->ReadFromStream(pStream, m_oHeader.RecInstance >= 5);
                        if (m_cLevels > 4)
                        {
                            m_lstLvl5 = new STextMasterStyleLevel;
                            m_lstLvl5->ReadFromStream(pStream, m_oHeader.RecInstance >= 5);
                        }
                    }
                }
            }
        }

        StreamUtils::StreamSeek(lPos + m_oHeader.RecLen, pStream);
    }
};
}
