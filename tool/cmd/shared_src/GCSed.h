//
//  GCSed.hpp
//  gx_sed
//
//  Created by Gengxin Gu on 16/4/21.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GCSed_hpp
#define GCSed_hpp

#include <QObject>


class GCSed : public QObject {
    Q_OBJECT
public:
    GCSed();
    ~GCSed();
    
private:
    QString m_FromStr;
    QString m_FromStrSuf;
    QString m_ToStr;
    QString m_FileStr;
};



#endif /* GCSed_hpp */
